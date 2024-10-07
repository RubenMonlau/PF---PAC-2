#include <iostream>
#include <vector>
#include <string>
#include <sqlite3.h>

using namespace std;

// Función para ejecutar una consulta SQL
bool ejecutarSQL(sqlite3* db, const string& sql) {
    char* errorMessage = nullptr;
    int result = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errorMessage);
    
    if (result != SQLITE_OK) {
        cerr << "Error SQL: " << errorMessage << endl;
        sqlite3_free(errorMessage);
        return false;
    }
    return true;
}

// Inicializar la base de datos si no existe y crear la tabla de usuarios si no existen.
void inicializarBD(sqlite3* db) {
    string sql = "CREATE TABLE IF NOT EXISTS Usuarios ("
                 "ID INTEGER PRIMARY KEY AUTOINCREMENT, "
                 "Nom TEXT NOT NULL, "
                 "Edat INTEGER NOT NULL);";
    ejecutarSQL(db, sql);
}

// Función para añadir un usuario a la base de datos
void añadirUsuario(sqlite3* db) {
    string nombre;
    int edad;

    cout << "Introduce el Nombre del usuario: ";
    cin.ignore();  // Limpiar el buffer
    getline(cin, nombre);
    cout << "Introduce la Edad del usuario: ";
    cin >> edad;

    string sql = "INSERT INTO Usuarios (Nom, Edat) VALUES ('" + nombre + "', " + to_string(edad) + ");";
    if (ejecutarSQL(db, sql)) {
        cout << "Usuario añadido correctamente.\n";
    }
}

// Función para eliminar un usuario de la base de datos
void eliminarUsuario(sqlite3* db) {
    int id;
    cout << "Introduce el ID del usuario a eliminar: ";
    cin >> id;

    string sql = "DELETE FROM Usuarios WHERE ID = " + to_string(id) + ";";
    if (ejecutarSQL(db, sql)) {
        cout << "Usuario eliminado correctamente.\n";
    }
}

// Función para modificar un usuario en la base de datos
void modificarUsuario(sqlite3* db) {
    int id;
    string nombre;
    int edad;

    cout << "Introduce el ID del usuario a modificar: ";
    cin >> id;
    cout << "Introduce el nuevo Nombre: ";
    cin.ignore();  // Limpiar el buffer
    getline(cin, nombre);
    cout << "Introduce la nueva Edad: ";
    cin >> edad;

    string sql = "UPDATE Usuarios SET Nom = '" + nombre + "', Edat = " + to_string(edad) + " WHERE ID = " + to_string(id) + ";";
    if (ejecutarSQL(db, sql)) {
        cout << "Usuario modificado correctamente.\n";
    }
}

// Función para mostrar todos los usuarios de la base de datos
static int callback(void* NotUsed, int argc, char** argv, char** azColName) {
    for (int i = 0; i < argc; i++) {
        cout << azColName[i] << ": " << (argv[i] ? argv[i] : "NULL") << " ";
    }
    cout << endl;
    return 0;
}

void mostrarUsuarios(sqlite3* db) {
    string sql = "SELECT * FROM Usuarios;";
    cout << "Usuarios en la base de datos:\n";
    sqlite3_exec(db, sql.c_str(), callback, nullptr, nullptr);
}

int main() {
    // Conectar a la base de datos SQLite
    sqlite3* db;
    int exit = sqlite3_open("BasedeDatosPersonal.db", &db);

    if (exit) {
        cerr << "Error al abrir la base de datos: " << sqlite3_errmsg(db) << endl;
        return -1;
    } else {
        cout << "Conexión a la base de datos exitosa.\n";
    }

    // Inicializar la base de datos (crear tabla si no existe)
    inicializarBD(db);

    int opcion;

    do {
        cout << "\n--- Menú Base de Datos de Usuarios ---\n";
        cout << "1. Mostrar todos los usuarios\n";
        cout << "2. Añadir un usuario\n";
        cout << "3. Eliminar un usuario\n";
        cout << "4. Modificar un usuario\n";
        cout << "5. Salir\n";
        cout << "Elige una opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                mostrarUsuarios(db);
                break;
            case 2:
                añadirUsuario(db);
                break;
            case 3:
                eliminarUsuario(db);
                break;
            case 4:
                modificarUsuario(db);
                break;
            case 5:
                cout << "Saliendo del programa...\n";
                break;
            default:
                cout << "Opción no válida. Inténtalo de nuevo.\n";
        }
    } while (opcion != 5);

    // Cerrar la conexión a la base de datos
    sqlite3_close(db);

    return 0;
}