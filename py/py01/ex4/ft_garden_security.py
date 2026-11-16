class Plant:
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
        if self._is_valid_height(height):
            self._height = height
        if self._is_valid_age(age_in_days):
            self._age_in_days = age_in_days
        self._starting_height = self._height

    def show(self) -> None:
        print(f"{self.name}: {self._height:.1f}cm, "
              f"{self._age_in_days} days old")

    def grow(self) -> None:
        self._height += self.growth_rate

    def age(self) -> None:
        self._age_in_days += 1

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


def main() -> None:
    print("=== Garden Security System ===")
    rose = Plant("Rose", 15.0, 10)
    print("Plant created", end=": ")
    rose.show()
    rose.set_height(25)
    rose.set_age(30)
    rose.set_height(-5)
    rose.set_age(-3)
    print("Current state", end=": ")
    rose.show()


if __name__ == "__main__":
    main()
