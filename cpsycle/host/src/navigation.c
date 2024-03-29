/*
** This source is free software ; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation ; either version 2, or (at your option) any later version.
** copyright 2000-2022 members of the psycle project http://psycle.sourceforge.net
*/

#include "../../detail/prefix.h"


#include "navigation.h"
/* host */
#include "resources/resource.h"
#include "styles.h"


/* protoypes*/
static void navigation_on_prev(Navigation*, psy_ui_Component* sender);
static void navigation_on_next(Navigation*, psy_ui_Component* sender);

/* implementation */
void navigation_init(Navigation* self, psy_ui_Component* parent,
	Workspace* workspace)
{
	assert(self);
	assert(workspace);
	
	psy_ui_component_init(&self->component, parent, NULL);
	self->workspace_ = workspace;
	psy_ui_component_set_style_type(navigation_base(self), STYLE_NAVBAR);
	psy_ui_component_set_default_align(navigation_base(self), psy_ui_ALIGN_LEFT,
		psy_ui_margin_make_em(0.0, 0.5, 0.0, 0.0));	
	psy_ui_component_set_align_expand(navigation_base(self), psy_ui_HEXPAND);
	psy_ui_button_init_connect(&self->prev_, navigation_base(self),
		self, navigation_on_prev);		
	psy_ui_button_load_resource(&self->prev_, IDB_ARROW_BACK_LIGHT,
		IDB_ARROW_BACK_DARK, psy_ui_colour_white());
	psy_ui_button_init_connect(&self->next_, navigation_base(self),
		self, navigation_on_next);	
	psy_ui_button_load_resource(&self->next_, IDB_ARROW_FORWARD_LIGHT,
		IDB_ARROW_FORWARD_DARK, psy_ui_colour_white());
}

void navigation_on_prev(Navigation* self, psy_ui_Component* sender)
{
	assert(self);
	
	workspace_back(self->workspace_);
}

void navigation_on_next(Navigation* self, psy_ui_Component* sender)
{
	assert(self);
	
	workspace_forward(self->workspace_);
}
