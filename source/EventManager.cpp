/*

  _   _                                      _              _ __            _
 | | | |   ___     ___      _ _     o O O   (_)    _ _     | '_ \  _  _    | |_
 | |_| |  (_-<    / -_)    | '_|   o        | |   | ' \    | .__/ | +| |   |  _|
  \___/   /__/_   \___|   _|_|_   TS__[O]  _|_|_  |_||_|   |_|__   \_,_|   _\__|
_|"""""|_|"""""|_|"""""|_|"""""| {======|_|"""""|_|"""""|_|"""""|_|"""""|_|"""""|
"`-0-0-'"`-0-0-'"`-0-0-'"`-0-0-'./o--000'"`-0-0-'"`-0-0-'"`-0-0-'"`-0-0-'"`-0-0-'

Martijn's brainstorm over hoe ik events ga doen, niet belangrijk om te lezen, maar staat erbij because.

Hoe gaan we dat doen dan?

Verwacht dat Brian een tcp socket thread heeft waar je mee kan verbinden, wat voor data hieroverheen gaat maakt nog niet zo veel uit...
Wat je dan doet is:

1: Leg verbinding met deze localhost:tcp verbinding
2: Als je input krijg, propagate deze events door naar alle Entities

Wat geven we entities dan? Je kan in cpp niet zo makkelijk callbacks doen, dus doen we hacky callbacks of doen we iets als
Entity::update(dt, InputInformation input)

Dan krijgen we wel eerder een probleem met pressed denk ik
Alhoewel valt wel mee

stel, A en B zijn knoppen, dit is een tijdlijn
A = onDown,
a = onRelease

Bij deze mogelijkheid moet je wel opletten met timing, als je een knop indrukt op t=0.3, en je frames update worden aangeroepen op t=0.29 en t=0.31, dan zou de knop wel moeten worden meegegeven bij t=0.31, ookal was hij toen niet actief.

Misschien is evented callbacks alsnog beter, ookal ziet dit er hacky als fuck uit. Dan hoef ik met veel minder rekening te houden qua timing, buffering etc
Het enige wat ik dan moet doen is bij de input handler een hashmap met function pointers bijhouden

Ok, voor de function pointer methode moet ik twee dingen hebben,

1. Een reference naar de callback methode
2. Een reference naar het object die deze methode bezit

Op zich geen probleem als ik in de constructor gewoon zoiets doe:

// of we doen een generiek EventObject
// of we maken twee verschillende events, een buttonevent en een movement event, anders krijg je voor horizontal movement en voor vertical movement een losse event handler

Sphere::onbuttonDown(EventObject input) {
    // input ziet er ong zo uit ofzo:
    // {
    //   origin: "bat1" // of bat2 of remote ofzo
    //   eventName: "buttonADown",
    //   eventValue: 1 // down
    // }
}

Sphere::onMovement(EventObject input) {
    // input ong:
    // {
    //   origin: "bat1",
    //   eventName: "HorizontalMovementEvent",
    //   eventValue: 3
    // }
}
 */

// events komen binnen vanaf de tcp verbinding, best wel fijn.

// we kunnen twee dingen doen, of we maken op een of andere manier een generieke InputEvent
// waar je al je data in kwijt kan, bijvoorbeeld
// {
//   eventType: "buttonEvent",
//
// }

// #include <vector>
// #include <map>
// 
// struct EventListener {
//     fnc_ptr callback;
//     Entity  *entity;
// };
//
// class EventManager {
// private:
//     // Socket                             connection;
//     map<string, vector<EventListener>> listeners;
// public:
//     register    (string eventName, fnc_ptr, Entity*);
//     unregister  (string eventName, fnc_ptr, Entity*);
//
//     EventManager();
// };
//
// EventManager::EventManager() {
//     // set up tcp socket stuff here
// }
//
// EventManager::register(string eventName, fnc_ptr callback, Entity *entity) {
//     listeners[eventName] = new EventListener(callback, entity);
// }
//
// EventManager::unregister(string eventName, fnc_ptr callback) {
//     // we don't need a reference to entity, since fnc_ptrs are unique already.
//     for (int i = 0; i < this->listeners[eventName].size(); i++) {
//         if (this->listeners[eventName].callback == callback) {
//             this->listeners[eventName].erase(i);
//         }
//     }
// }
