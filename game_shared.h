#ifndef GAME_SHARED_H
#define GAME_SHARED_H

#include <stdbool.h>

// ==========================================
// 1. DEFINICIONES DE TIPOS (ENUMS)
// ==========================================

// Tipos de Unidades
typedef enum {
  UNIT_ALDEANO, // Auto-spawn
  UNIT_CAZADOR, // (Quizás obsoleto si el aldeano caza, pero se mantiene por si
                // acaso)
  UNIT_SAQUEADOR,
  UNIT_GUARDIAS,
  UNIT_ARQUERAS,
  UNIT_CABALLERO,
  UNIT_CANONERO,
  UNIT_MEGACABALLERO,

  // Barcos
  SHIP_EXPLORADOR,
  SHIP_TACTICO,
  SHIP_ACORAZADO,

  UNIT_TYPE_COUNT
} UnitType;

// Tipos de Edificios (NUEVO)
typedef enum {
  BUILDING_FORTALEZA,  // Central
  BUILDING_CHOZA,      // Aldeanos
  BUILDING_CAMPAMENTO, // Tropas
  BUILDING_MUELLE,     // Barcos
  BUILDING_FABRICA_ELIXIR,

  // Defensas
  BUILDING_TORRE_ARQUERAS,
  BUILDING_CANON_DEF,
  BUILDING_MORTERO,
  BUILDING_MURALLA,

  // Almacenes
  BUILDING_ALMACEN_ORO,
  BUILDING_ALMACEN_COMIDA,
  BUILDING_ALMACEN_MATERIA, // Madera y Roca

  BUILDING_TYPE_COUNT
} BuildingType;

// Tipos de Recursos (Cambiado a 5: +Elixir)
typedef enum {
  RES_COMIDA,
  RES_MADERA,
  RES_ROCA,
  RES_ORO,
  RES_ELIXIR,
  RES_COUNT
} ResourceType;

// ==========================================
// 2. ESTRUCTURAS DE DATOS (STRUCTS)
// ==========================================

// Inventario del Jugador con Capacidades
typedef struct {
  int comida;
  int max_comida;

  int madera;
  int max_madera;

  int roca;
  int max_roca;

  int oro;
  int max_oro;

  int elixir;
  int max_elixir;
} Resources;

// Estructura de Unidad Individual
typedef struct Unit {
  int id;
  UnitType type;
  int hp;
  int max_hp;
  int attack;
  int level;
  float x, y;
  bool is_water_unit;
  struct Unit *next;
} Unit;

// Stats Base para el Database
typedef struct {
  char name[30];
  int base_hp;
  int base_attack;
  int speed;
  int range;

  // Costos (Sin diamantes)
  int cost_comida;
  int cost_madera;
  int cost_roca;
  int cost_oro;

  bool is_ship;
} UnitStats;

// Prototipos
// void init_game_database();
// extern UnitStats UNIT_DATABASE[UNIT_TYPE_COUNT];

#endif // GAME_SHARED_H
