class Plant:
    def __init__(self,
                 name: str,
                 height: float,
                 age_in_days: int,
                 growth_rate: float = 1.0
                 ) -> None:
        self.name = name
        self.height = height
        self.starting_height = height
        self.age_in_days = age_in_days
        self.growth_rate = growth_rate

    def show(self) -> None:
        print(f"{self.name}: {self.height:.1f}cm, {self.age_in_days} days old")

    def grow(self) -> None:
        self.height += self.growth_rate

    def age(self) -> None:
        self.age_in_days += 1


def main() -> None:
    plants = [Plant("Rose", 25.0, 30),
              Plant("Oak", 200.0, 365),
              Plant("Cactus", 5, 90, 0.35),
              Plant("Sunflower", 80, 45),
              Plant("Fern", 15, 120)
              ]

    print("=== Plant Factory Output ===")

    for plant in plants:
        print("Created", end=": ")
        plant.show()


if __name__ == "__main__":
    main()
