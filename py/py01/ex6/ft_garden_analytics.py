class Plant:
    class _Stats:
        def __init__(self) -> None:
            self._grow_calls = 0
            self._age_calls = 0
            self._show_calls = 0

        def count_grow(self) -> None:
            self._grow_calls += 1

        def count_age(self) -> None:
            self._age_calls += 1

        def count_show(self) -> None:
            self._show_calls += 1

        def display(self) -> None:
            print(f"Stats: {self._grow_calls} grow, "
                  f"{self._age_calls} age, "
                  f"{self._show_calls} show")

    def __init__(self,
                 name: str,
                 height: float,
                 age_in_days: int,
                 growth_rate: float = 1.0
                 ) -> None:
        self.name = name
        self._height = 0.0
        self._age_in_days = 0
        self.growth_rate = growth_rate
        self._stats = Plant._Stats()
        if self._is_valid_height(height):
            self._height = height
        if self._is_valid_age(age_in_days):
            self._age_in_days = age_in_days
        self._starting_height = self._height

    @staticmethod
    def is_older_than_year(days: int) -> bool:
        return days > 365

    @classmethod
    def anonymous(cls) -> "Plant":
        return cls("Unknown plant", 0.0, 0)

    def show(self) -> None:
        self._stats.count_show()
        print(f"{self.name}: {self._height:.1f}cm, "
              f"{self._age_in_days} days old")

    def show_stats(self) -> None:
        self._stats.display()

    def grow(self) -> None:
        self._stats.count_grow()
        self._height += self.growth_rate

    def age(self, days: int = 1) -> None:
        self._stats.count_age()
        self._age_in_days += days

    def get_height(self) -> float:
        return self._height

    def get_age(self) -> int:
        return self._age_in_days

    def _is_valid_height(self, value: float) -> bool:
        if value < 0:
            print(f"{self.name}: Error, height can't be negative")
            return False
        return True

    def _is_valid_age(self, value: int) -> bool:
        if value < 0:
            print(f"{self.name}: Error, age can't be negative")
            return False
        return True

    def set_height(self, value: float) -> None:
        if not self._is_valid_height(value):
            print("Height update rejected")
            return
        self._height = value
        print(f"Height updated: {value}cm")

    def set_age(self, value: int) -> None:
        if not self._is_valid_age(value):
            print("Age update rejected")
            return
        self._age_in_days = value
        print(f"Age updated: {value} days")


class Flower(Plant):
    def __init__(self,
                 name: str,
                 height: float,
                 age_in_days: int,
                 color: str,
                 growth_rate: float = 1.0
                 ) -> None:
        super().__init__(name, height, age_in_days, growth_rate)
        self.color = color
        self.blooming = False

    def bloom(self) -> None:
        self.blooming = True

    def show(self) -> None:
        super().show()
        print(f"Color: {self.color}")
        if self.blooming:
            print(f"{self.name} is blooming beautifully!")
            return
        print(f"{self.name} has not bloomed yet")


class Seed(Flower):
    def __init__(self,
                 name: str,
                 height: float,
                 age_in_days: int,
                 color: str,
                 seeds_when_bloomed: int,
                 growth_rate: float = 1.0
                 ) -> None:
        super().__init__(name, height, age_in_days, color, growth_rate)
        self._seeds_when_bloomed = seeds_when_bloomed
        self._seeds = 0

    def bloom(self) -> None:
        super().bloom()
        self._seeds = self._seeds_when_bloomed

    def show(self) -> None:
        super().show()
        print(f"Seeds: {self._seeds}")


class Tree(Plant):
    class _TreeStats(Plant._Stats):
        def __init__(self) -> None:
            super().__init__()
            self._shade_calls = 0

        def count_shade(self) -> None:
            self._shade_calls += 1

        def display(self) -> None:
            super().display()
            print(f"{self._shade_calls} shade")

    def __init__(self,
                 name: str,
                 height: float,
                 age_in_days: int,
                 trunk_diameter: float,
                 growth_rate: float = 1.0
                 ) -> None:
        super().__init__(name, height, age_in_days, growth_rate)
        self.trunk_diameter = trunk_diameter
        self._stats: Tree._TreeStats = Tree._TreeStats()

    def produce_shade(self) -> None:
        self._stats.count_shade()
        print(f"Tree {self.name} now produces a shade of "
              f"{self.get_height():.1f}cm long and "
              f"{self.trunk_diameter:.1f}cm wide.")

    def show(self) -> None:
        super().show()
        print(f"Trunk diameter: {self.trunk_diameter:.1f}cm")


class Vegetable(Plant):
    def __init__(self,
                 name: str,
                 height: float,
                 age_in_days: int,
                 harvest_season: str,
                 growth_rate: float = 1.0
                 ) -> None:
        super().__init__(name, height, age_in_days, growth_rate)
        self.harvest_season = harvest_season
        self.nutritional_value = 0

    def age(self, days: int = 1) -> None:
        super().age(days)
        self.nutritional_value += days

    def show(self) -> None:
        super().show()
        print(f"Harvest season: {self.harvest_season}")
        print(f"Nutritional value: {self.nutritional_value}")


def display_stats(plant: Plant) -> None:
    print(f"[statistics for {plant.name}]")
    plant.show_stats()


def main() -> None:
    print("=== Garden statistics ===")
    print("=== Check year-old")
    for days in (30, 400):
        print(f"Is {days} days more than a year? -> "
              f"{Plant.is_older_than_year(days)}")

    print("\n=== Flower")
    rose = Flower("Rose", 15.0, 10, "red", 8.0)
    rose.show()
    display_stats(rose)
    print("[asking the rose to grow and bloom]")
    rose.grow()
    rose.bloom()
    rose.show()
    display_stats(rose)

    print("\n=== Tree")
    oak = Tree("Oak", 200.0, 365, 5.0)
    oak.show()
    display_stats(oak)
    print("[asking the oak to produce shade]")
    oak.produce_shade()
    display_stats(oak)

    print("\n=== Seed")
    sunflower = Seed("Sunflower", 80.0, 45, "yellow", 42, 30.0)
    sunflower.show()
    print("[make sunflower grow, age and bloom]")
    sunflower.grow()
    sunflower.age(20)
    sunflower.bloom()
    sunflower.show()
    display_stats(sunflower)

    print("\n=== Anonymous")
    unknown = Plant.anonymous()
    unknown.show()
    display_stats(unknown)


if __name__ == "__main__":
    main()
