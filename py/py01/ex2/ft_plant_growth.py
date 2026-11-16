class Plant:
    def __init__(self,
                 name: str,
                 height: float,
                 growth_rate: float,
                 age_in_days: int) -> None:
        self.name = name
        self.height = height
        self.starting_height = height
        self.age_in_days = age_in_days
        self.growth_rate = growth_rate

    def show(self) -> None:
        print(f"{self.name}: {self.height:.2f}cm, {self.age_in_days} days old")

    def grow(self) -> None:
        self.height += self.growth_rate

    def age(self) -> None:
        self.age_in_days += 1


def main() -> None:
    plants = [Plant("Rose", 24.7, 0.25, 26),
              Plant("Sunflower", 83.5, 0.35, 43),
              Plant("Cactus", 17.3, 0.1, 130)]
    print("=== Garden Plant Registry ===")
    for day in range(1, 8):
        print(f"\n--- Day {day} ---")
        for plant in plants:
            plant.grow()
            plant.age()
            plant.show()
    print("\n--- Growth this week ---")
    for plant in plants:
        print(f"{plant.name}: {plant.height - plant.starting_height:.2f}cm")


if __name__ == "__main__":
    main()
