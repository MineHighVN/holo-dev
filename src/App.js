const { _holo, holo } = require("@holo/dev");

const App = () => {
    holo.window.setTitle("Holo Project (@holo/dev)");

    return _holo("p", {
        children: `Hello world from @holo/dev`,
    });
};

module.exports = App;
