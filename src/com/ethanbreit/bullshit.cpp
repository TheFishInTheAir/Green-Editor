#include <bullshit.h>



#include <stdlib.h>
#include <string.h>
#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#define NK_IMPLEMENTATION
#include <GL/glew.h>
#include <nuklear.h>
#define NK_GLFW_GL3_IMPLEMENTATION
#include <nuklear_glfw_gl3.h>


//BULLSHIT START
#include <ge/entity/component/components/AudioListinerComponent.h>
#include <ge/entity/component/components/AudioSourceComponent.h>
#include <ge/entity/component/components/CameraComponent.h>
#include <ge/entity/component/components/DirectionalLightComponent.h>
#include <ge/entity/component/components/EngineControllerComponent.h>
#include <ge/entity/component/components/FreeCamControllerComponent.h>
#include <ge/entity/component/components/HLMeshComponent.h>
#include <ge/entity/component/components/MeshRendererComponent.h>
#include <ge/entity/component/components/PointLightComponent.h>
#include <ge/entity/component/components/RuntimeMaterialComponent.h>
#include <ge/entity/component/components/SpotLightComponent.h>
#include <ge/entity/component/components/SpotLightShadowComponent.h>
#include <ge/entity/component/components/TransformComponent.h>
#include <ge/engine/scene/Scene.h>

void _lol_this_doesnt_work_nk_draw_image(struct nk_command_buffer *b, struct nk_rect r,
	const struct nk_image *img, struct nk_color col)
{
	struct nk_command_image *cmd;
	//NK_ASSERT(b);
	if (!b) return;
	if (b->use_clipping) {
		const struct nk_rect *c = &b->clip;
		if (c->w == 0 || c->h == 0 || !NK_INTERSECT(r.x, r.y, r.w, r.h, c->x, c->y, c->w, c->h))
			return;
	}

	cmd = (struct nk_command_image*)
		nk_command_buffer_push(b, NK_COMMAND_IMAGE, sizeof(*cmd));
	if (!cmd) return;
	cmd->x = (short)r.x;
	cmd->y = (short)r.y;
	//cmd->w = (unsigned short)NK_MAX(0, r.w);
	//cmd->h = (unsigned short)NK_MAX(0, r.h);
	cmd->w = (unsigned short)NK_MAX(0, r.w);
	cmd->h = (unsigned short)NK_MAX(0, r.h);
	cmd->img = *img;
	cmd->col = col;
}


void __this_is_bullshit_i_need_to_get_this_shit_to_work()
{
	ge::Scene::currentScene = new ge::Scene();

	ge::Entity* BULL_FUCKING_SHIT = new ge::Entity();
	ge::AudioListinerComponent* alc = new ge::AudioListinerComponent(BULL_FUCKING_SHIT);
	ge::AudioSourceComponent* asc = new ge::AudioSourceComponent(BULL_FUCKING_SHIT);
	ge::CameraComponent* cc = new ge::CameraComponent(BULL_FUCKING_SHIT);
	ge::DirectionalLightComponent* dc = new ge::DirectionalLightComponent(BULL_FUCKING_SHIT);
	ge::EngineControllerComponent* ecc = new ge::EngineControllerComponent(BULL_FUCKING_SHIT);
	ge::FreeCamControllerComponent* fccc = new ge::FreeCamControllerComponent(BULL_FUCKING_SHIT);
	ge::HLMeshComponent* hlmc = new ge::HLMeshComponent(BULL_FUCKING_SHIT);
	ge::MeshRendererComponent* mrc = new ge::MeshRendererComponent(BULL_FUCKING_SHIT);
	ge::PointLightComponent* plc = new ge::PointLightComponent(BULL_FUCKING_SHIT);
	ge::RuntimeMaterialComponent* rmc = new ge::RuntimeMaterialComponent(BULL_FUCKING_SHIT);
	ge::SpotLightComponent* slc = new ge::SpotLightComponent(BULL_FUCKING_SHIT);
	ge::SpotLightShadowComponent* slsc = new ge::SpotLightShadowComponent(BULL_FUCKING_SHIT);
	ge::TransformComponent* tc = new ge::TransformComponent(BULL_FUCKING_SHIT);

	alc->destroy();
	asc->destroy();
	cc->destroy();
	dc->destroy();
	ecc->destroy();
	fccc->destroy();
	hlmc->destroy();
	mrc->destroy();
	plc->destroy();
	rmc->destroy();
	slc->destroy();
	slsc->destroy();
	tc->destroy();
	BULL_FUCKING_SHIT->destroy();


	free(alc);
	free(asc);
	free(cc);
	free(dc);
	free(ecc);
	free(fccc);
	free(hlmc);
	free(mrc);
	free(plc);
	free(rmc);
	free(slc);
	free(slsc);
	free(tc);

	free(BULL_FUCKING_SHIT);
}
//BULLSHIT END