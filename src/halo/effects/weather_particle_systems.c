void weather_particle_systems_initialize(void)
{
  weather_particle_system_data = data_new("weather particles", 0x200, 0x54);
  if (weather_particle_system_data == 0)
    error(0, "couldn't allocate weather particle system globals.");
}

void weather_particle_systems_initialize_for_new_map(void)
{
  int16_t i;
  int *entry;

  i = 0;
  entry = (int *)0x4557f4;
  do {
    assert_halt(i >= 0 && i < MAXIMUM_NUMBER_OF_LOCAL_PLAYERS);
    *entry = NONE;
    i++;
    entry = (int *)((char *)entry + 0x9c);
  } while (i < 4);
  *(int16_t *)0x4557f0 = 0;
  data_delete_all(weather_particle_system_data);
}

void weather_particle_systems_dispose_from_old_map(void)
{
  if (weather_particle_system_data && weather_particle_system_data->valid)
    data_make_invalid(weather_particle_system_data);
}

void weather_particle_systems_dispose(void)
{
  if (weather_particle_system_data) {
    data_dispose(weather_particle_system_data);
    weather_particle_system_data = 0;
  }
}
/* --- weather_particle_systems.obj batch drafts (2026-07-26) --- */

/* 0xa3e60 */
void FUN_000a3e60(void)
{

}

/* 0xa3ea0 */
void FUN_000a3ea0(void)
{

}

/* 0xa4000 */
void FUN_000a4000(void)
{

}

/* 0xa40a0 */
void weather_particle_system_new(void)
{

}

/* 0xa4200 */
void weather_particle_system_delete(void)
{

}

/* 0xa4310 */
void FUN_000a4310(void)
{

}

/* 0xa45d0 */
void FUN_000a45d0(void)
{

}

/* 0xa4610 */
void FUN_000a4610(void)
{

}

/* 0xa48c0 */
void FUN_000a48c0(void)
{

}

/* 0xa4a00 */
void FUN_000a4a00(void)
{

}

/* 0xa4ab0 */
void FUN_000a4ab0(void)
{

}

/* 0xa4be0 */
void FUN_000a4be0(void)
{

}

/* 0xa4e20 */
void weather_particle_system_render(void)
{

}
