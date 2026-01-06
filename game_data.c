#include "game_shared.h"
#include <string.h>

UnitStats UNIT_DATABASE[UNIT_TYPE_COUNT];

void init_game_database()
{
  // Puntero auxiliar
  UnitStats *s;

  // --- TIERRRA ---

  // 1. GUARDIAS
  s = &UNIT_DATABASE[UNIT_GUARDIAS];
  strcpy(s->name, "Guardia Real");
  s->base_hp = 90;
  s->base_attack = 12;
  s->cost_oro = 50;
  s->cost_comida = 20;

  // 2. CABALLERO
  s = &UNIT_DATABASE[UNIT_CABALLERO];
  strcpy(s->name, "Caballero");
  s->base_hp = 160;
  s->base_attack = 18;
  s->cost_oro = 120;
  s->cost_comida = 60;

  // 3. SAQUEADOR
  s = &UNIT_DATABASE[UNIT_SAQUEADOR];
  strcpy(s->name, "Saqueador");
  s->base_hp = 80;
  s->base_attack = 10;
  s->cost_oro = 25;
  s->cost_comida = 10;

  // 4. ARQUERAS
  s = &UNIT_DATABASE[UNIT_ARQUERAS];
  strcpy(s->name, "Arquera");
  s->base_hp = 70;
  s->base_attack = 15;
  s->range = 10; // Rango medio
  s->cost_oro = 80;
  s->cost_madera = 40; // Arcos de madera

  // 5. CAÑONERO
  s = &UNIT_DATABASE[UNIT_CANONERO];
  strcpy(s->name, "Cañonero");
  s->base_hp = 120;
  s->base_attack = 35;
  s->range = 20; // Rango alto
  s->cost_oro = 200;
  s->cost_madera = 50;
  s->cost_roca = 20; // Balas de cañón?

  // 6. MEGACABALLERO (La Bestia)
  // Antes costaba diamantes, ahora es muy caro en recursos
  s = &UNIT_DATABASE[UNIT_MEGACABALLERO];
  strcpy(s->name, "MEGACABALLERO");
  s->base_hp = 600;
  s->base_attack = 45;
  s->cost_oro = 600;
  s->cost_comida = 300; // Come mucho
  s->cost_roca = 100;   // Armadura pesada

  // --- NAVAL (COMBATE) ---

  // 7. BARCO EXPLORADOR
  s = &UNIT_DATABASE[SHIP_EXPLORADOR];
  strcpy(s->name, "Explorador");
  s->base_hp = 200;
  s->base_attack = 10;
  s->is_ship = true;
  s->cost_madera = 100;

  // 8. BARCO TÁCTICO (Caza-Barcos)
  s = &UNIT_DATABASE[SHIP_TACTICO];
  strcpy(s->name, "Destructor Táctico");
  s->base_hp = 350;
  s->base_attack = 30; // Daño decente contra otros barcos
  s->is_ship = true;
  s->cost_madera = 250;
  s->cost_oro = 100;

  // 9. BARCO ACORAZADO (Tanque Naval)
  s = &UNIT_DATABASE[SHIP_ACORAZADO];
  strcpy(s->name, "Acorazado de Guerra");
  s->base_hp = 800;    // Muy resistente
  s->base_attack = 60; // Cañonazo fuerte
  s->is_ship = true;
  s->cost_madera = 500;
  s->cost_oro = 300;
  s->cost_roca = 100; // Refuerzos
}
