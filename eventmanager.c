#include <stdlib.h>

#include <SDL2/SDL.h>

#include "common.h"
#include "resourcemanager.h"
#include "eventmanager.h"

struct Event* events[EVENTS_MAX] = { 0 };

void em_register_key(SDL_Keycode key, Callback call, VoidFn onevent,
	                 uint16 count, intptr data1, intptr data2)
{
	uint16 i = 0;
	while (events[i]) i++;

	struct Event* e = smalloc(sizeof(struct Event));
	e->key      = key;
	e->type     = EVENT_KEY;
	e->count    = count;
	e->callback = call;
	e->onevent  = onevent;
	e->data1    = data1;
	e->data2    = data2;
	events[i]   = e;
}

// struct Event* _event_register_key(SDL_Keycode key, uint16 count)
// {
// 	uint16 i = 0;
// 	while (events[i]) i++;

// 	struct Event* e = malloc(sizeof(struct Event));
// 	e->type   = EVENT_KEY;
// 	e->count  = count;
// 	e->key    = key;
// 	events[i] = e;

// 	return e;
// }

// void _event_register_key_t(SDL_Keycode key, Trigger trigger, uint16 count)
// {
// 	struct Event* e = _event_register_key(key, count);
// 	e->trigger = TRIGGER;
// 	e->call    = trigger;
// }

// void _event_register_key_kt(SDL_Keycode key, KeyTrigger trigger, uint16 count)
// {
// 	struct Event* e = _event_register_key(key, count);
// 	e->trigger = KEY_TRIGGER;
// 	e->keycall = trigger;
// }

// void _event_register_key_tt(SDL_Keycode key, TimedTrigger trigger, uint16 count)
// {
// 	struct Event* e = _event_register_key(key, count);
// 	e->trigger   = TIMED_TRIGGER;
// 	e->timedcall = trigger;
// }

void em_update(double dt)
{
	(void)dt; // TODO: timed events
	struct Event* event;
	SDL_Event sdlevent;
	while (SDL_PollEvent(&sdlevent)) {
		if (sdlevent.type == SDL_KEYDOWN && !sdlevent.key.repeat) {
			for (uint8 i = 0; i < EVENTS_MAX; i++) {
				event = events[i];
				if (!event || event->type != EVENT_KEY) {
					continue;
				} else if (event->key == sdlevent.key.keysym.sym) {
					/* Check to see if the event is infinite or not */
					if (event->count) {
						event->callback(event, true);
						event->count--;
						/* Non-infinite events are removed once their counter reaches 0 */
						if (!event->count) {
							free(event);
							events[i] = NULL;
						}
					} else {
						event->callback(event, true);
					}
				}
			}
		} else if (sdlevent.type == SDL_KEYUP) {
			for (uint8 i = 0; i < EVENTS_MAX; i++) {
				event = events[i];
				if (!event) {
					continue;
				} else if (event->key == sdlevent.key.keysym.sym) {
					event->callback(event, false);
				}
			}
		}
	}
}
