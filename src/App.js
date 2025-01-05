const { _holo, holo, css } = require("@holo/dev");
const path = require("path");

const styles = css.loadAndParse(path.join(__dirname, "./main.css"));

const HelloWorld = ({ children }) => {
    return _holo("p", {
        children: ["Hello world from ", children],
    });
};

const TestComponent = () => {
    return _holo("fragment", {
        children: [
            _holo("p", {
                children: `Hello world from @holo/dev`,
            }),
            _holo("p", {
                children: "Author: MineHighVN",
            }),
            _holo(HelloWorld, {
                children: "MineHighVN",
            }),
        ],
    });
};

const App = () => {
    holo.window.setTitle("Holo Project (@holo/dev)");

    return _holo("div", {
        children: _holo(TestComponent),
    });
};

module.exports = App;
