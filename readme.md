# Todo API with Emscripten 🚀

This project demonstrates how to fetch and display a list of todos from a remote API using C++ and Emscripten. The fetched data is displayed in an HTML table 📝.

## Project Structure 📂

- `todoapi.cpp`: The main C++ source file that contains the logic for fetching and displaying todos.

## Explanation ℹ️

- The `fetchTodos` function uses Emscripten's Fetch API to make an HTTP GET request to `https://dummyjson.com/todos` 🌐.
- On success, the fetched data is parsed and displayed in an HTML table 🗂️.
- On error, an error message is printed to the console ❌.

## WebAssembly 🕸️

This project uses WebAssembly to run C++ code in the browser 🌍. Emscripten compiles the C++ code into WebAssembly, allowing it to interact with JavaScript and the DOM ⚙️.
