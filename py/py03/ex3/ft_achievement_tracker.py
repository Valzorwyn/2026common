import random

ACHIEVEMENTS = [
    "Crafting Genius",
    "World Savior",
    "Master Explorer",
    "Collector Supreme",
    "Untouchable",
    "Boss Slayer",
    "Strategist",
    "Unstoppable",
    "Speed Runner",
    "Survivor",
    "Treasure Hunter",
    "First Steps",
    "Sharp Mind",
    "Hidden Path Finder",
]


def gen_player_achievements() -> set[str]:
    count = random.randint(5, 9)
    return set(random.sample(ACHIEVEMENTS, count))


def main() -> None:
    players = [
        ("Alice", gen_player_achievements()),
        ("Bob", gen_player_achievements()),
        ("Charlie", gen_player_achievements()),
        ("Dylan", gen_player_achievements())
    ]
    print("=== Achievement Tracker System ===")
    for name, achievements in players:
        print(f"Player {name}: {achievements}")
    all_achievements: set[str] = set()
    for _, achievements in players:
        all_achievements = all_achievements.union(achievements)
    print(f"\nAll distinct achievements: {all_achievements}")
    common_achievements = players[0][1]
    for _, achievements in players:
        common_achievements = common_achievements.intersection(achievements)
    print(f"\nCommon achievements: {common_achievements}\n")
    for name, achievements in players:
        others: set[str] = set()
        for other_name, other_achievement in players:
            if other_name != name:
                others = others.union(other_achievement)
        print(f"Only {name} has: {achievements.difference(others)}")
    print("\n")
    every_achievement = set(ACHIEVEMENTS)
    for name, achievements in players:
        print(f"{name} is missing: "
              f"{every_achievement.difference(achievements)}")


if __name__ == "__main__":
    main()
