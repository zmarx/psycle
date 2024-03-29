/*
** This source is free software ; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation ; either version 2, or (at your option) any later version.
** copyright 2000-2022 members of the psycle project http://psycle.sourceforge.net
*/

#include "../../detail/prefix.h"


#include "dummy.h"
/* local */
#include "plugin_interface.h"


const psy_audio_MachineInfo* psy_audio_dummymachine_info(void)
{
	static psy_audio_MachineInfo const macinfo = {
		MI_VERSION,
		0x0250,
		EFFECT | 32 | 64,
		psy_audio_MACHMODE_FX,
		"Dummy plug"
			#ifndef NDEBUG
			" (debug build)"
			#endif
			,		
		"Dummy",
		"Psycledelics",
		"help",		
		psy_audio_DUMMY,
		0,
		0,		
		"",
		"",
		"mixer",
		psy_INDEX_INVALID,
		""
	};
	return &macinfo;
}

static const psy_audio_MachineInfo* info(psy_audio_DummyMachine* self) {
	return psy_audio_dummymachine_info();
}
static intptr_t mode(psy_audio_DummyMachine* self) { return self->mode; }
static uintptr_t numinputs(psy_audio_DummyMachine* self) { return 2; }
static uintptr_t numoutputs(psy_audio_DummyMachine* self) { return 2; }

static MachineVtable vtable;
static bool vtable_initialized = FALSE;

static void vtable_init(psy_audio_DummyMachine* self)
{
	if (!vtable_initialized) {
		vtable = *self->custommachine.machine.vtable;
		vtable.mode = (fp_machine_mode)mode;
		vtable.info = (fp_machine_info)info;
		vtable.numinputs = (fp_machine_numinputs)numinputs;
		vtable.numoutputs = (fp_machine_numoutputs)numoutputs;
		vtable_initialized = TRUE;
	}
	self->custommachine.machine.vtable = &vtable;
}

void psy_audio_dummymachine_init(psy_audio_DummyMachine* self,
	psy_audio_MachineCallback* callback)
{
	assert(self);

	self->mode = psy_audio_MACHMODE_FX;
	psy_audio_custommachine_init(&self->custommachine, callback);
	vtable_init(self);
	psy_audio_custommachine_set_amp_range(&self->custommachine,
		PSY_DSP_AMP_RANGE_IGNORE);	
}
