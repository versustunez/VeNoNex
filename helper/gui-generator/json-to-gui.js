const fs = require("fs"),
    baseIn = "./guis/",
    baseOut = "./../../Source/Veno/GUI/",
    files = [
        {
            src: "oscgui.json",
            tpl: "oscgui.tpl",
            out: "Components/PageComponents/Oscillators/OscillatorGUISetup.cpp"
        },
        {
            src: "lfogui.json",
            tpl: "lfogui.tpl",
            out: "Components/PageComponents/Modulators/LFOGUISetup.cpp"
        },
    ]
let content = "";

function depth(depth) {
    for (let i = 0; i < depth; i++) {
        content += "    ";
    }
}

function prepareName(item, id) {
    let name;
    if (item.indexOf("{id}") === 0) {
        name = `\"${item.replace("{id}", "")}\"`;
        if (name === "\"\"" && id) {
            name = id;
        } else if (id) {
            name = `${id} + ${name}`;
        }
    } else {
        name = `"${item}"`;
    }
    return name;
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
    for (let file of files) {
        let tpl = fs.readFileSync(baseIn + file.tpl, "utf8").toString(),
            json = JSON.parse(fs.readFileSync(baseIn + file.src, "utf-8").toString());
        content = "";
        generateBlocks(json.blocks);
        tpl = tpl.replace("$b$", content);
        content = "";
        generateComponents(json.items);
        tpl = tpl.replace("$g$", content);
        fs.writeFileSync(baseOut + file.out, tpl);
    }
}

generate();
