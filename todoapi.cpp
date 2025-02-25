#include <iostream>
#include <emscripten.h>
#include <emscripten/fetch.h>

extern "C" {
    void fetchTodos();
}

void fetchTodos() {
    emscripten_fetch_attr_t attr;
    emscripten_fetch_attr_init(&attr);
    strcpy(attr.requestMethod, "GET");
    attr.attributes = EMSCRIPTEN_FETCH_LOAD_TO_MEMORY;
    attr.onsuccess = [](emscripten_fetch_t *fetch) {
        std::cout << "Fetched " << fetch->numBytes << " bytes\n";
        std::cout << "Response: " << fetch->data << std::endl;
        EM_ASM_({
            var todos = JSON.parse(UTF8ToString($0)).todos;
            var resultDiv = document.getElementById('result');
            var table = document.createElement('table');
            var header = '<tr><th>ID</th><th>Todo</th><th>Completed</th><th>UserID</th></tr>';
            table.innerHTML = header;

            todos.forEach(todo => {
                var completed = todo.completed ? 'Yes' : 'No';
                var row = '<tr><td>' + todo.id + '</td><td>' + todo.todo + '</td><td>' + completed + '</td><td>' + todo.userId + '</td></tr>';
                table.innerHTML += row;
            });

            resultDiv.appendChild(table);
        }, fetch->data);
        emscripten_fetch_close(fetch);
    };
    attr.onerror = [](emscripten_fetch_t *fetch) {
        std::cout << "Failed to fetch " << fetch->url << std::endl;
        emscripten_fetch_close(fetch);
    };
    emscripten_fetch(&attr, "https://dummyjson.com/todos");
}

int main() {
    EM_ASM({
        var resultDiv = document.createElement('div');
        resultDiv.id = 'result';
        document.body.appendChild(resultDiv);
    });
    fetchTodos();
    return 0;
}

// Windows
// docker run --rm -v ${PWD}:/src emscripten/emsdk emcc /src/bmi.cpp -o /src/index.html --emrun -s FETCH=1 --shell-file /src/index.html

// Linux/Mac
// docker run --rm -v $(pwd):/src emscripten/emsdk emcc /src/todoapi.cpp -o /src/index.html --emrun -s FETCH=1 --shell-file /src/index.html
