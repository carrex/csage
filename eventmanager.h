#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#define EVENTS_MAX 64

enum EventType {
	EVENT_KEY,
	EVENT_MOUSE,
	EVENT_MOUSEMOVE,
	EVENT_TIME,
};

struct Event {
	union {
		SDL_Keycode key;
	};
	enum EventType type;
	uint16 count;
	void (*callback)(struct Event*, bool);
	VoidFn onevent;
	intptr data1;
	intptr data2;
};

typedef void (*Callback)(struct Event*, bool);

void em_register_key(SDL_Keycode key, Callback call, VoidFn onevent,
	                 uint16 count, intptr data1, intptr data2);
void em_update(double dt);

inline static void em_callback_(struct Event* e, bool kdown)
{
	e->onevent();
}
inline static void em_callback_b(struct Event* e, bool kdown)
{
	((void (*)(bool))e->onevent)(kdown);
}
inline static void em_callback_bd(struct Event* e, bool kdown)
{
	((void (*)(bool, intptr))e->onevent)(kdown, e->data1);
}
inline static void em_callback_bdd(struct Event* e, bool kdown)
{
	((void (*)(bool, intptr, intptr))e->onevent)(kdown, e->data1, e->data2);
}

#define CB_NONE        ((Callback)em_callback_)
#define CB_KDOWN       ((Callback)em_callback_b)
#define CB_KDOWN_DATA1 ((Callback)em_callback_bd)
#define CB_KDOWN_DATA2 ((Callback)em_callback_bdd)

#endif
