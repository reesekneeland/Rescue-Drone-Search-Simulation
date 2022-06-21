# Understanding picojson and the front-end
This is an optional lab provided as an extra resource.

## Objective
Develop a better understanding of what json is and how the library picojson manipulates and 
communicates this information with the front-end system. 

## Background
The front-end is a graphical interface developed using javascript and a popular library known as 
THREE.js. THREE.js is very powerful with many of it's complex functionality abstracted to single 
function calls. The library is built off of WebGL and has been tuned to leverage system hardware 
for optimal performance. Javascript is the most commonly used language in the world however it does 
have its limitations. It is a scripting language designed off a paradigm known as ecmascript. It is 
lightweight, dynamically typed, and supports higher order functions. Javscript supports its own 
style of data communication known as JSON (JavasSript Object Notation). JSON is a hash rather than 
an array and is similar to python dictionaries, which use hash tables to match the keys to arrays. 
JSON is transmitted over networks as a string.

## Getting Started
Considering that C++ is a statically typed language, it grows obvious that there will be challenges 
in converting a string with embedded dynamic types. This is why we use picojson. It is a 
lightweight header-only library that does this for us. However, it can be complicated understanding 
it for the first time so we will began with an example.
```
{
    "entityId": 0,
    "name": "drone",
    "type": "actor",
    "path": "drone.glb",
    "position": [0, 2.5, 0],
    "scale": [0.15, 0.15, 0.15],
    "rotation": [0, 0, 0],
    "direction": [0, 0, 0],
    "charge": 20.0,
    "speed": 4.0,
    "radius": 1.0,
    "start": 2.0,
    "duration": 2.0,
    "offset": [0, 0.6, 0]
}
```
From this JSON data structure we can see that there is an array, a string, a double and an integer. 
To begin, we will start by retrieving the hash that is passed as a picojson::value. In this 
picojson::value exists an object. Objects in javascript are often written in shorthand as data 
surrounded in curly braces. Since you will not be dealing with the specific task of managing send 
and receive calls, you only need to worry about the primary picojson::object in web_app.cc. However; 
for those who are curious, this object is retrieved with the following function.
```
void WebApp::receiveJSON(picojson::value& val) {
    if (val.is<picojson::object>) {
        picojson::object o = val.get<picojson::object>();
    }
}
```
From here this object is passed into our ReceiveCommand function in WebApp. This is where you will 
extract the information yourselves and assign it to classes as needed. Before extracting the information, 
lets take a second to discuss how picojson works under the hood. Picojson uses a std::pair to 
represent (key, value) pairs. If we had a pair pointer named p, p->first will get us the key, and 
p->second will get us the value. This still does not solve our dynamically typed problem though. 
To solve this issue, we use the picojson get function which converts the value into our desired type 
by means of templating. A quick note... Picojson only supports double numerical values, therefore 
floats and integers will have to be casted after extracted. Lastly, in iterating a picojson object, 
the c++ iterator library is used, as well as a map to optimize key searching in larger datasets. 
Extracting the above information can be done with the following code.
```
int id = static_cast<int>(o.find("entityId")->second.get<double>());
std::string name = o.find("type")->second.get<std::string>();
picojson::array arr = o.find("position")->second.get<picojson::array>();
std::vector<float> position = {0, 0, 0};
for (int i = 0; i < arr.size(); i++) {
    position.at(i) = static_cast<float>(arr[i].get<double>());
}
```
## Creating JSON to send back
For those who are pursuing the observer pattern, specific naming conventions
will be needed when sending information back to the front-end. There will be a separate lab on the 
observer pattern, but for now the parameters below are interpreted in the front-end to provide 
certain display functionality when implemented. Display information is a common use for the observer 
pattern, as display information is changing frequently. To create a picojson::object, and send it 
back, the following code can be used in web_app.cc
```
picojson::object info;
info["type"] = picojson::value("battery");
info["data"] = picojson::value(1.0);
picojson::object o;
o["notification"] = picojson::value(info);
picojson::value v(o);
this->Send(v);
```
This creates the following JSON value.
```
[
    "notification": {
        "type": "battery",
        "data": 1.0
    }
]
```
## Retrieving map data
The path searching strategy pattern will require map data. We provide two json files: nodes.json 
and edges.json (stored in the project/data directory). Nodes.json is a list of node ids and their corresponding positions. The second file, 
edges.json, is another list of ids but with an array of its adjacent nodes. These adjacent nodes are 
represented by ids. Therefore a lookup in nodes.json will be required in to find the nodes position. 
To parse these files we will again be using picojson. Code to iterate this data structure can be 
done as follows.
```
std::ifstream nodes("nodes.json");
std::stringstream buf;
buf << nodes.rdbuf();
std::string json = buf.str();
picojson::value v;
std::string err = picojson::parse(v, json);
if (!err.empty()) {
    std:cerr << err << std::endl;
} else {
    printf("picojson parsed\n");
}

if (v.is<picojson::array>()) {
    picojson::array arr = v.get<picojson::array>();
    int prefix = 0;
    for (int i = 0; i < arr.size(); i++) {
        if (arr[i].is<picojson::object>()) {
            picojson::object o = arr[i].get<picojson::object>();
            for (picojson::object::const_iterator it = o.begin(); it != o.end(); it++) {
                // can uncomment for printed visualization of data
                // std::cout << prefix << " " << it->first << ": " << it->second << std::endl;
                prefix++;

                // the key is an id (i.e. "1716439481")

                // the return value format is as follows
                // { "position":
                //     "x": 841,
                //     "y": 264,
                //     "z": 704
                // }

                // TODO: Create a graph with the parsed information

            }
        } else {
            printf("array value is not a picojson::object\n");
        }
    }
} else {
    printf("value is not an array\n");
}

```
## A Brief on Graph Theory
The two json files (nodes.json and edges.json) provide the necessary graph information. A parser 
for nodes.json was provided. It is your task to parse edges.json and in combination with the parsed 
information from nodes.json, create a graph class so that you can conduct path-searching. 
(Hint: edges.json is very similar to nodes.json, but instead of the parsed value being a 
picojson::object with x, y, z values, the value is a picojson::array) An example: 
```
("4111674105": ["723893259", "1762637754]);
```
Your task is to build this graph structure and compute various search algorithms such as A* and DFS. 
To guide you toward a direction that does not involve an algorithm that takes minutes to compute, 
we recommend you use the unordered_map stl of c++. Storing all the nodes and mapping their ids to 
positions will increase look up time ten fold. From here, parsing the edges file and assigning a 
std::vector of neighbor ids to the node id will allow you to look up their positions quickly. This should 
give you what you need to compute the graph traversal algorithms. If you are confused by graph theory, 
please feel free to reach out to one of the TAs or surf the internet on what a graph adjacency list is.