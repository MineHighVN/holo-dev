**# Holo Project**

**A Note on Development**

> This is a **development version**.
> Holo Project is currently designed for product demonstration and is incomplete.
> Please refrain from evaluating the product while it is under development.

**What is Holo Project?**

Holo Project offers a revolutionary approach to building user interfaces. With a familiar syntax similar to **ReactJS**, developers can effortlessly write code using a component-based model. However, instead of relying on **WebView**, all rendering is handled directly by **C++**, resulting in exceptional performance.

This not only significantly reduces system resource consumption but also enhances responsiveness and user experience. Developers no longer need to worry about performance bottlenecks or sluggish applications caused by embedded browsers, as is common with traditional frameworks.

-   **C++** is employed to handle window rendering, leveraging the language's low-level control and performance capabilities.
-   **Node.js** manages the application logic, providing simplicity and extensibility through JavaScript's rich ecosystem.

Holo Project is designed as a lightweight alternative to heavyweight desktop application development tools like **Electron**, minimizing system resource usage while maintaining flexibility and ease of use.

**Key Features:**

-   **High Performance:** Leverages the power of C++ for the frontend.
-   **Easy Development:** Node.js offers a straightforward development environment with numerous supporting libraries.
-   **Lightweight and Efficient:** Consumes fewer resources than traditional solutions, making Holo Project suitable for performance-critical applications.
-   **Familiar Syntax:** If you're familiar with ReactJS, you'll find Holo Project easy to adopt.
-   **No WebView:** Holo Project completely eliminates WebView, replacing it with a high-performance rendering interface powered by C++.
-   **Resource Optimization:** Applications are optimized for efficient operation, consuming less RAM and CPU compared to other frameworks.
-   **Unified Environment:** Combines the power of **JavaScript** for logic handling and **C++** for building interfaces, all within a cohesive ecosystem.
-   **Open Source:** Anyone can contribute, customize, and enhance the project.

**Usage**

The structure of HoloJS is almost identical to React. The `_holo` function functions similarly to `_jsx` in React. However, since HoloJS doesn't currently use Babel, you'll need to write `_holo` with the following structure:

> HTML

```html
<p>Hello world from @holo/dev</p>
```

> HoloJS

```js
_holo("p", {
    children: "Hello world from @holo/dev",
});
```

When written in full, the code will look like this:

```js
const { _holo, holo } = require("@holo/dev");

const App = () => {
    holo.window.setTitle("Holo Project (@holo/dev)");

    return _holo("p", {
        children: `Hello world from @holo/dev`,
    });
};

module.exports = App;
```

**Installation**

Currently, Holo Project has only been tested on Linux (Kubuntu 24.04.1 LTS x86_64) and may encounter errors on Windows.

To install Holo Project, follow these steps:

1. Clone from the holo-dev repository

```bash
git clone https://github.com/MineHighVN/holo-dev
cd holo-dev
```

2. Install required libraries

```bash
npm install
```

3. Install GLFW

```bash
sudo apt install libglfw3-dev
```

4. Run the application in development mode

```bash
npm run dev
```

It will take some time to launch the first time because it may have to build the necessary C++ libraries for NodeJS
