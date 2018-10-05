#pragma once
struct nk_context;
void draw_inspector(nk_context* ctx);

void set_inspection_content(void(*function)(nk_context*, void*), void* meta);
void set_inspection_content(void(*function)(nk_context*, void*), void* meta, bool should_free);

void draw_ent_inspector(nk_context* ctx);
void* get_current_inspection_meta();
