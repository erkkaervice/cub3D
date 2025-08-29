# cub3D
RayCaster with miniLibX


📝 Post-Parsing Integration Checklist
1. Replace Mock Config
 Remove or disable the mock data in cfg.c.

 Use t_config filled by partner’s parser.

 Verify:

map is correctly allocated and terminated with NULL.

Texture paths (north_texture, etc.) are valid strings from parsing.

Floor/ceiling colors are parsed integers or RGB structs.

2. Hook Parsing into Main
 Call parsing before init_game(&game).

 If parsing fails → print error, cleanup_game(&game), return (1).

 Ensure MLX is not initialized unless parsing succeeds.

3. Texture Loading
 Update textures.c to load from game.cfg->north_texture, etc.

 Handle missing or invalid texture paths gracefully.

 Confirm all textures match the required .xpm42 format.

4. Map Usage
 Ensure render_minimap() and raycasting use the parsed map directly.

 Confirm player spawn position/angle from parsing is applied to:

game.player_x

game.player_y

game.player_angle

5. Error & Cleanup
 If texture loading fails after MLX init → free loaded textures and terminate MLX.

 If parsing fails before MLX init → only free parsed data (map, strings).

 Make sure no double frees occur when cleanup is called after partial init.

6. Final Validation
 Test with subject’s sample maps.

 Test with invalid maps (holes, bad chars) → should exit cleanly.

 Test bonus features (doors, minimap) with parsed maps.

Optional Bonus
 Animated doors.

 HUD elements.

 Sprite animation.