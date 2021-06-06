const fs = require("fs"),
    baseIn = "./guis/",
    baseOut = "./../../Source/Veno/GUI/Components/PageComponents/",
    files = {
        osc: "Oscillators/OscillatorGUISetup.cpp",
        lfo: "Modulators/LFOGUISetup.cpp",
        envelope: "Modulators/EnvelopeGUISetup.cpp"
    };
let content = "";

function getFileContents(filename) {
    return fs.readFileSync(filename, "utf8").toString();
}

function depth(depth) {
    for (let i = 0; i < depth; i++) {
        content += "    ";
    }
}

function prepareName(item, id) {
    if (item.indexOf("{id}") === 0) {
        if (id) {
            if (item.length > 4) {
                return `${id} + "${item.substring(4)}"`;
            }
            return id;
        }
    }
    return `"${item}"`;
}

function generateBlocks(blocks) {
    for (let item of blocks) {
        content += "\n";
        depth(2);
        content += `m_helper->m_blocks.push_back({"${item.name}", ${item.x},${item.y},${item.w},${item.h}});`;
    }
}

function generateComponents(items) {
    for (let item of items) {
        content += "\n";
        depth(2);
        let type = "VeNoSelect::Type::NoSelect";
        if (item.type === "box") {
            type = "VeNoSelect::Type::" + item.seType;
        }
        content += `m_helper->createItem({"${item.type}", ${prepareName(item.parameter, "m_name")},"${item.name}",${item.x},${item.y},${item.w},${item.h}, ${type}});`;
    }
}

function generate() {
    for (let name in files) {
        let tpl = getFileContents(baseIn + name + "gui.tpl"),
            json = JSON.parse(getFileContents(baseIn + name + "gui.json"));
        content = "";
        generateBlocks(json.blocks);
        tpl = tpl.replace("$b$", content);
        content = "";
        generateComponents(json.items);
        tpl = tpl.replace("$g$", content);
        fs.writeFileSync(baseOut + files[name], tpl);
    }
}

generate();
