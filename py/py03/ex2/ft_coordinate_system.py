import math

Coords = tuple[float, float, float]


def get_player_pos() -> Coords:
    while True:
        pos = input("Enter new coordinates as floats in format 'x,y,z': ")
        try:
            x, y, z = pos.split(",")
        except ValueError:
            print("Invalid syntax")
            continue
        coords = []
        for coord in (x, y, z):
            try:
                coords.append(float(coord))
            except ValueError as e:
                print(f"Error on parameter {coord!r}: {e}")
                break
        else:
            return (coords[0], coords[1], coords[2])


def distance(a: Coords, b: Coords) -> float:
    x1, y1, z1 = a
    x2, y2, z2 = b
    return math.sqrt((x2 - x1) ** 2 + (y2 - y1) ** 2 + (z2 - z1) ** 2)


def main() -> None:
    print("=== Game Coordinate System ===")
    print("Get a first set of coordinates")
    first = get_player_pos()
    x, y, z = first
    print(f"Got a first tuple: {first}")
    print(f"It includes: X={x}, Y={y}, Z={z}")
    distance_to_center = distance((0.0, 0.0, 0.0), first)
    print(f"Distance to center: {round(distance_to_center, 4)}")
    print("Get a second set of coordinates")
    second = get_player_pos()
    distance_between_coords = distance(first, second)
    print(f"Distance between the 2 sets of coordinates: "
          f"{round(distance_between_coords, 4)}")


if __name__ == "__main__":
    main()
