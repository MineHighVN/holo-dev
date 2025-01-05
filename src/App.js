const { _holo, holo } = require("@holo/dev");

const HelloWorld = ({ children }) => {
    return _holo("p", {
        children: `Hello world from ${children}`,
    });
};

const TestComponent = () => {
    return _holo("Fragment", {
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
