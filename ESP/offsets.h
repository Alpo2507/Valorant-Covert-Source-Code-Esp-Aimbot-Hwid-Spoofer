#pragma once
#ifndef OFFSETS_H
#define OFFSETS_H

uint64_t BaseAddr = (uintptr_t)GetModuleHandleA(0);

namespace offsets {
	constexpr uintptr_t uworld_key = 0x8E7D138;
	constexpr uintptr_t uworld_state = 0x8E7D100;

	constexpr uintptr_t game_instance = 0x1A8; // world + game_instance // TYPE=uintptr_t
	constexpr uintptr_t persistent_level = 0x38; // world + persistent_level // TYPE=uintptr_t

	constexpr uintptr_t local_player_array = 0x40; // game_instance + local_player_array // TYPE=uintptr_t
	constexpr uintptr_t local_player_controller = 0x38; // local_player + local_player_controller // TYPE=uintptr_t
	constexpr uintptr_t local_player_pawn = 0x440; // local_player_controller + local_player_pawn // TYPE=uintptr_t (=actor)
	constexpr uintptr_t control_rotation = 0x420; // local_player_controller + control_rotation // TYPE=Vector3

	constexpr uintptr_t camera_manager = 0x458; // local_player_controller + camera_manager // TYPE=uintptr_t
	constexpr uintptr_t camera_position = 0x1220; // camera_manager + camera_position // TYPE=Vector3
	constexpr uintptr_t camera_rotation = 0x122C; // camera_manager + camera_rotation // TYPE=Vector3
	constexpr uintptr_t camera_fov = 0x1238; // camera_manager + camera_fov // TYPE=float

	constexpr uintptr_t actor_array = 0xA0; // persistent_level + actor_array // TYPE=uintptr_t
	constexpr uintptr_t actor_count = 0xb8; // persistent_level + actor_count // TYPE=int

	constexpr uintptr_t ObjID = 0x18; // actor + actor_id // TYPE=uintptr_t
	constexpr uintptr_t unique_id = 0x38; // actor + actor_id // TYPE=uintptr_t
	constexpr uintptr_t mesh_component = 0x410; // actor + mesh_component // TYPE=uintptr_t
	constexpr uintptr_t static_mesh = 0x558;
	constexpr uintptr_t static_mesh_cached = 0x568;
	constexpr uintptr_t last_render_time = 0x350; // mesh_component + last_render_time // TYPE=float
	constexpr uintptr_t last_submit_time = 0x358; // mesh_component + last_submit_time // TYPE=float
	constexpr uintptr_t bone_array = 0x558; // mesh_component + bone_array // TYPE=uintptr_t
	constexpr uintptr_t bone_count = 0x560; // actor + bone_count // TYPE=uintptr_t
	constexpr uintptr_t component_to_world = 0x250; // mesh_component + component_to_world // TYPE=uintptr_t
	constexpr uintptr_t root_component = 0x210; // actor + root_component // TYPE=uintptr_t
	constexpr uintptr_t root_position = 0x164; // root_component + root_position // TYPE=Vector3
	constexpr uintptr_t damage_handler = 0x978	; // actor/local_player_pawn + damage_handler // TYPE=uintptr_t
	constexpr uintptr_t health = 0x1b0; // damage_handler + health // TYPE=float
	constexpr uintptr_t velocity = 0xfc; // root_component + velocity // type= float
	constexpr uintptr_t dormant = 0x100; // actor + dormant // TYPE=bool
	constexpr uintptr_t fresnel_intensity = 0x690;
	constexpr uintptr_t player_state = 0x3D0; // actor/local_player_pawn + player_state // TYPE=uintptr_t
	constexpr uintptr_t team_component = 0x580; // player_state + team_component // TYPE=uintptr_t
	constexpr uintptr_t team_id = 0xF8; // team_component + team_id // TYPE=int

	constexpr uintptr_t LineOfSightTo = 0x4C83EC0;
}
#endif