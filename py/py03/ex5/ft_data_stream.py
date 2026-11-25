import random
from typing import Generator

PLAYERS = ["alice", "bob", "charlie", "dylan"]

ACTIONS = [
    "run",
    "eat",
    "sleep",
    "grab",
    "move",
    "climb",
    "swim",
    "use",
    "release",
]

Event = tuple[str, str]


def gen_event() -> Generator[Event, None, None]:
    while True:
        yield (random.choice(PLAYERS), random.choice(ACTIONS))


def consume_event(events: list[Event]) -> Generator[Event, None, None]:
    while events:
        yield events.pop(random.randrange(len(events)))


def main() -> None:
    print("=== Game Data Stream Processor ===")
    stream = gen_event()
    for i in range(1000):
        name, action = next(stream)
        print(f"Event {i}: Player {name} did action {action}")
    events = [next(stream) for _ in range(10)]
    print(f"Built list of 10 events: {events}")
    for event in consume_event(events):
        print(f"Got event from list: {event}")
        print(f"Remains in list: {events}")


if __name__ == "__main__":
    main()
