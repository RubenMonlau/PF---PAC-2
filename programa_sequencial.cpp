#include <iostream>
#include <sqlite3.h>

using namespace std;

// Funció per executar una consulta SQL i mostrar els resultats
static int callback(void* NotUsed, int argc, char** argv, char** azColName) {
    for (int i = 0; i < argc; i++) {
        cout << azColName[i] << ": " << (argv[i] ? argv[i] : "NULL") << endl;
    }
    return 0;
}

int main() {
    sqlite3* DB;
    int exit = sqlite3_open("exemple.db", &DB);

    if (exit) {
        cerr << "Error a la base de dades: " << sqlite3_errmsg(DB) << endl;
        return -1;
    } else {
        cout << "Connexió a la base de dades feta amb èxit!" << endl;
    }

    // Crear una taula si no existeix
    string create_table_query = "CREATE TABLE IF NOT EXISTS usuaris (ID INT, Nom TEXT, Edat INT);";
    exit = sqlite3_exec(DB, create_table_query.c_str(), NULL, 0, NULL);

    if (exit != SQLITE_OK) {
        cerr << "Error creant la taula" << endl;
        sqlite3_close(DB);
        return -1;
    }

    // Inserir un valor
    string insert_query = "INSERT INTO usuaris (ID, Nom, Edat) VALUES (1, 'Joan', 30);";
    exit = sqlite3_exec(DB, insert_query.c_str(), NULL, 0, NULL);

    if (exit != SQLITE_OK) {
        cerr << "Error inserint les dades" << endl;
        sqlite3_close(DB);
        return -1;
    }

    // Mostrar el valor
    string select_query = "SELECT * FROM usuaris;";
    exit = sqlite3_exec(DB, select_query.c_str(), callback, NULL, NULL);

    if (exit != SQLITE_OK) {
        cerr << "Error mostrant les dades" << endl;
        sqlite3_close(DB);
        return -1;
    }

    // Modificar el valor
    string update_query = "UPDATE usuaris SET Edat = 31 WHERE ID = 1;";
    exit = sqlite3_exec(DB, update_query.c_str(), NULL, 0, NULL);

    if (exit != SQLITE_OK) {
        cerr << "Error actualitzant les dades" << endl;
        sqlite3_close(DB);
        return -1;
    }

    cout << "Valor modificat correctament." << endl;

    // Tornar a mostrar el valor després de la modificació
    exit = sqlite3_exec(DB, select_query.c_str(), callback, NULL, NULL);

    sqlite3_close(DB);
    return 0;
}
