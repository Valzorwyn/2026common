import random

PLAYERS = [
    "Alice",
    "bob",
    "Charlie",
    "dylan",
    "Emma",
    "Gregory",
    "john",
    "kevin",
    "Liam",
]


def main() -> None:
    capitalised = [player.capitalize() for player in PLAYERS]
    now_upper = [player for player in PLAYERS if player[0].isupper()]
    print("=== Game Data Alchemist ===")
    print(f"Initial list of players: {PLAYERS}")
    print(f"New list with all names capitalized: {capitalised}")
    print(f"New list of capitalized names only: {now_upper}")
    scores = {player: random.randint(0, 1000) for player in capitalised}
    print(f"Score dict: {scores}")
    average = sum([scores[player] for player in scores]) / len(scores)
    print(f"Score average is {round(average, 2)}")
    high = {player: scores[player] for player in scores
            if scores[player] > average}
    print(f"High scores: {high}")


if __name__ == "__main__":
    main()
