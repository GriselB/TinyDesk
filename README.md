# 🧾 TinyDesk – Sistema de Gestión de Proyectos y Tickets

**Integrantes del equipo:**

- Maximiliano Bianchi
- Sebastian Yanni
- Marian Grisel Morales Bonadies
- Marcelo Adrián Rearte Becerra

**Repositorio:** https://github.com/GriselB/TinyDesk

---

## 📌 1. Introducción

**TinyDesk** es un sistema de gestión de proyectos y tickets inspirado en herramientas como **Jira** y **ClickUp**.  
Permite organizar tareas, gestionar equipos de trabajo y obtener métricas de rendimiento tanto individuales como grupales.

El objetivo principal es ofrecer una plataforma **intuitiva, escalable y adaptable** a metodologías ágiles (principalmente **SCRUM**), con trazabilidad y reportes automáticos.

---

## 🎯 2. Visión

Ser una herramienta integral de gestión de proyectos que potencie la **colaboración, transparencia y eficiencia**, permitiendo tomar decisiones basadas en datos reales del progreso del equipo.

---

## 🚀 3. Misión

Proporcionar una plataforma **accesible y dinámica** para planificar, ejecutar y analizar proyectos mediante la gestión de:

- Tickets
- Sprints
- Roles y usuarios

Todo orientado a entornos de trabajo ágiles.

---

## 🛠️ 4. Descripción General del Sistema

El sistema está desarrollado en **C++ (consola)** y utiliza archivos de persistencia **.dat / .csv** para almacenar los datos.

### 🔹 Entidades principales:

| Entidad  | Descripción                              |
| -------- | ---------------------------------------- | ---------------------------- |
| Proyecto | Agrupa tickets, sprints y usuarios       |
| Usuario  | Personas que interactúan con el sistema  |
| Roles    | Administrador, Líder o Colaborador       |
| Áreas    | Sector o departamento asignado           |
| Sprint   | Períodos de trabajo planificado          |
| Ticket   | Tareas a realizar                        | alta, media o baja prioridad |
| Estado   | Pendiente, En progreso, Finalizado, etc. |

---

## 📦 5. Módulos Funcionales

### ✅ **a. Login y Autenticación**

- Validación de email y contraseña
- Control de acceso según rol
- Registro de actividad y último inicio de sesión

### ✅ **b. Gestión de Proyectos**

- Crear, modificar, cerrar y listar proyectos
- Asociar sprints y tickets a cada proyecto

### ✅ **c. Gestión de Usuarios y Roles**

- Alta, baja y modificación de usuarios
- Asignación de roles y áreas
- Activación / desactivación de cuentas

### ✅ **d. Gestión de Sprints**

- Creación de sprints por proyecto
- Definición de fechas, estado y área
- Control del avance

### ✅ **e. Gestión de Tickets**

- Crear, asignar y cerrar tickets
- Priorización (alta, media, baja)
- Relación con usuario y sprint correspondiente

### ✅ **f. Reportes y Métricas**

- Cálculo automático de indicadores de desempeño
- Visualización de productividad, tiempos y prioridades

---

## 📋 6. Listados Disponibles

| Listado   | Contenido                                         |
| --------- | ------------------------------------------------- |
| Proyectos | Nombre, estado, avance, cantidad de tickets       |
| Usuarios  | Nombre, rol, área, tickets asignados              |
| Tickets   | Filtrado por proyecto, sprint, estado o prioridad |
| Sprints   | Fechas, progreso, tickets incluidos               |
| Áreas     | Usuarios activos y tareas en ejecución            |

---

## 🔍 7. Consultas del Sistema

Se pueden realizar consultas dinámicas según:

- Proyecto, usuario, rol, estado o prioridad
- Fechas de creación o finalización
- Porcentaje de avance o área
- Reportes generados automáticamente

---

## 📊 8. Reportes del Sistema

| Reporte                   | Descripción                                   |
| ------------------------- | --------------------------------------------- |
| ✅ Avance de proyecto     | % de tickets completados por proyecto         |
| ✅ Cumplimiento de sprint | Tareas finalizadas dentro del tiempo estimado |
| ✅ Productividad usuario  | Tareas completadas vs asignadas               |
| ✅ Prioridad de tickets   | Distribución: Alta, Media, Baja               |
| ✅ Tiempo de resolución   | Promedio de días por ticket                   |
| ✅ Actividad de usuario   | Último login, tickets creados/cerrados        |

---

## 💻 9. Requisitos del Sistema

- **Lenguaje:** C++
- **Persistencia:** Archivos `.dat`
- **Entorno recomendado:** Consola (Windows / Linux)
- **Compiladores sugeridos:** Code::Blocks, Dev-C++, Visual Studio

---

## 🔮 10. Futuras Mejoras

- Implementar interfaz gráfica (GUI)
- Migración a base de datos SQL
- Dashboard visual de métricas
- Sistema de notificaciones automáticas

---

## ✅ 11. Conclusión

TinyDesk es el primer paso hacia una plataforma **ágil, funcional y escalable** para la gestión de proyectos.  
Su diseño modular permite incorporar nuevas funciones y evolucionar hacia un entorno más visual, colaborativo e interactivo.
