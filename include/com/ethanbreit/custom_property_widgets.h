#pragma once
#include <string>
#include <glm/glm.hpp>

#include <ge/engine/enum/DataTypes.h>


struct nk_context;

void draw_ep_auto(nk_context* ctx, std::string name, ge::DataType::type t, void* v, int id);

void draw_ep_float(nk_context* nctx, std::string name, float*);
void draw_ep_bool(nk_context* nctx, std::string name, bool *v);
void draw_ep_int(nk_context* nctx, std::string name, int *v);
void draw_ep_material(nk_context* nctx, std::string name, std::string* text);
void draw_ep_texture(nk_context* nctx, std::string name, std::string* text);
void draw_ep_mesh_data(nk_context* nctx, std::string name, std::string* text);
void draw_ep_audio_clip(nk_context* nctx, std::string name, std::string* text);
void draw_ep_shader_group(nk_context* nctx, std::string name, std::string* text);
void draw_ep_quaternion(nk_context* nctx, std::string name, glm::quat *v, int id);
void draw_ep_vec3(nk_context* nctx, std::string name, glm::vec3 *v, int id);
void draw_ep_col3(nk_context* nctx, std::string name, glm::vec3 *v, int id);

