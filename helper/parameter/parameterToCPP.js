const fs = require("fs"),
    config = {
        tpl: fs.readFileSync("./template.tpl", "utf8").toString(),
        json: JSON.parse(fs.readFileSync("./parameters.json", "utf8"))
    };

let parameters = "";
const root = config.json.root;

function depth(depth) {
    for (let i = 0; i < depth; i++) {
        parameters += "    ";
    }
}

function prepareName(item, id, showId) {
    let name = `\"${item.name.replace("{id}__", "")}\"`;
    let showName = `\"${item.showName.replace("{sid}", "")}\"`;
    if (id) {
        name = `${id} + ${name}`;
    }
    if (showId) {
        showName = `${showId} + ${showName}`;
    }
    return {showName, name};
}

function createItem(item, tDepth, id, showID, i) {
    depth(tDepth);
    parameters += `// ${item.tooltip}\n`;
    let pre = prepareName(item, id, showID),
        name = pre.name,
        showName = pre.showName;
    let value = item.value;
    if (value === "{i} == 1") {
        value = "i == 1";
    }

    depth(tDepth);
    if (item.modulateAble) {
        parameters += `addParameterModulate (${name}, ${showName}, ${item.minValue}, ${item.maxValue}, ${value}, ${item.type});\n`;
    } else {
        parameters += `addParameter (${name}, ${showName}, ${item.minValue}, ${item.maxValue}, ${value}, ${item.type});\n`;
    }
}

function createForType(items, config) {
    let count = config.count + 1;
    parameters += `\n    for (int i = 1; i < ${count}; i++)\n    {\n`;
    depth(2);
    parameters += `std::string ${config.id}Id = "${config.id}" + std::to_string (i) + "__";\n`;
    depth(2);
    parameters += `std::string ${config.sid}Name = "${config.sid}" + std::to_string (i);\n`;
    for (let item of items) {
        createItem(item, 2, `${config.id}Id`, `${config.sid}Name`);
    }
    parameters += "    }\n";
}

console.log("[ParameterHandler] Generating Root");
for (let item of root) {
    createItem(item, 1);
}
console.log("[ParameterHandler] Generating Oscillator");
createForType(config.json.osc, config.json.oscConfig);
console.log("[ParameterHandler] Generating LFO");
createForType(config.json.lfo, config.json.lfoConfig);
console.log("[ParameterHandler] Generating Done.. Writing to File!");
fs.writeFileSync("./../../Source/Veno/Core/ParameterHandlerSetup.cpp", config.tpl.replace("$s$", parameters));
console.log("[ParameterHandler] Exit");