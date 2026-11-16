
class Plant:
    def __init__(self, name: str, height: float, age: int) -> None:
        self.name = name
        self.height = height
        self.age = age

    def show(self) -> None:
        print(f"{self.name}: {self.height}cm, {self.age} days old")


def main() -> None:
    plants = [Plant("Rose", 24.7, 26),
              Plant("Sunflower", 83.4, 43),
              Plant("Cactus", 17.3, 130)]
    print("=== Garden Plant Registry ===")
    for plant in plants:
        plant.show()


if __name__ == "__main__":
    main()
