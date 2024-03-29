/*
** This source is free software ; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation ; either version 2, or (at your option) any later version.
**  copyright 2000-2021 members of the psycle project http://psycle.sourceforge.net
*/

#if !defined(SEQEDITLINE_H)
#define SEQEDITLINE_H

#include "../../detail/psyconf.h"

#ifdef PSYCLE_USE_SEQEDITOR

/* host */
#include "seqeditorstate.h"
/* ui */
#include <uicomponent.h>

#ifdef __cplusplus
extern "C" {
#endif

/* SeqEditorLine */
typedef struct SeqEditorLine {
	/*! @extends  */
	psy_ui_Component component;	
	/* references */
	SeqEditState* state;
} SeqEditorLine;

void seqeditorline_init(SeqEditorLine*, psy_ui_Component* parent,
	SeqEditState*);

SeqEditorLine* seqeditorline_alloc(void);
SeqEditorLine* seqeditorline_allocinit(psy_ui_Component* parent,
	SeqEditState*);

void seqeditorline_updateposition(SeqEditorLine*, psy_dsp_beatpos_t position);

INLINE psy_ui_Component* seqeditorline_base(SeqEditorLine* self)
{
	return &self->component;
}

/* SeqEditorPlayline */
typedef struct SeqEditorPlayline {
	/*! @extends  */
	SeqEditorLine seqeditorline;
	/*! @internal */
	bool drag;
	double dragbase;	
} SeqEditorPlayline;

void seqeditorplayline_init(SeqEditorPlayline*, psy_ui_Component* parent,
	SeqEditState*);

SeqEditorPlayline* seqeditorplayline_alloc(void);
SeqEditorPlayline* seqeditorplayline_allocinit(psy_ui_Component* parent,
	SeqEditState*);
void seqeditorplayline_update(SeqEditorPlayline*);

INLINE psy_ui_Component* seqeditorplayline_base(SeqEditorPlayline* self)
{
	return seqeditorline_base(&self->seqeditorline);
}

#ifdef __cplusplus
}
#endif

#endif /* PSYCLE_USE_SEQEDITOR */

#endif /* SEQEDITLINE_H */
