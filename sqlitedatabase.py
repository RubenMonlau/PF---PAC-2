import sqlite3

# Codigo para visaulizar la base de datos en python

# Conectar a la base de datos
conn = sqlite3.connect('BasedeDatosPersonal.db')

# Crear un cursor
cursor = conn.cursor()

# Ejecutar una consulta para ver los datos de una tabla
cursor.execute("SELECT * FROM usuarios")

# Obtener todos los resultados
rows = cursor.fetchall()

# Mostrar los resultados
for row in rows:
    print(row)

# Cerrar la conexión
conn.close()
