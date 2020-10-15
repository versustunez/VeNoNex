const fs = require("fs"),
    config = {
        tpl: fs.readFileSync("./template.tpl", "utf8").toString(),
        json: JSON.parse(fs.readFileSync("./oscgui.json", "utf8"))
    };

let content = "";

function depth(depth) {
    for (let i = 0; i < depth; i++) {
        content += "    ";
    }
}

function prepareName(item, id) {
    let name = `\"${item.replace("{id}", "")}\"`;
    if (id) {
        name = `${id} + ${name}`;
    }
    return name;
}

function generateBlocks() {
    for (let item of config.json.blocks) {
        content += "\n";
        depth(2);
        content += `m_blocks.push_back({"${item.name}", ${item.x},${item.y},${item.w},${item.h}});`;
    }
}

function generateComponents() {
    for (let item of config.json.items) {
        content += "\n";
        depth(2);
        let type = "VeNoSelect::Type::NoSelect";
        if (item.type === "box") {
            type = "VeNoSelect::Type::" + item.seType;
        }
        content += `createItem({"${item.type}", ${prepareName(item.parameter, "m_name")},"${item.name}",${item.x},${item.y},${item.w},${item.h}, ${type}});`;
    }
}

function generate() {
    let tpl = config.tpl;
    content = "";
    generateBlocks();
    tpl = tpl.replace("$b$", content);
    content = "";
    generateComponents();
    tpl = tpl.replace("$g$", content);
    fs.writeFileSync("./../../Source/Veno/GUI/Components/Oscillator/OscillatorGUISetup.cpp", tpl);
}

generate();
