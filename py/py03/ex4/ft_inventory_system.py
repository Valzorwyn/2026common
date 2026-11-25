import sys


def parse_inventory(args: list[str]) -> dict[str, int]:
    """Build the inventory from 'name:quantity' arguments."""
    inventory: dict[str, int] = {}
    for arg in args:
        try:
            name, value = arg.split(":")
        except ValueError:
            print(f"Error - invalid parameter {arg!r}")
            continue
        if name in inventory:
            print(f"Redundant item {name!r} - discarding")
            continue
        try:
            quantity = int(value)
        except ValueError as e:
            print(f"Quantity error for {name!r}: {e}")
            continue
        if quantity < 0:
            print(f"Quantity error for {name!r}: negative quantity")
            continue
        inventory[name] = quantity
    return inventory


def main() -> None:
    """Display the inventory analysis."""
    print("=== Inventory System Analysis ===")
    inventory = parse_inventory(sys.argv[1:])
    print(f"Got inventory: {inventory}")
    print(f"Item list: {list(inventory.keys())}")
    total = sum(inventory.values())
    if total != 0:
        print(f"Total quantity of the {len(inventory)} "
              f"items: {total}")
        for item in inventory:
            percent = round(inventory[item] / total * 100, 1)
            print(f"Item {item} represents {percent}%")
        most = list(inventory.keys())[0]
        least = list(inventory.keys())[0]
        for item in inventory:
            if inventory[item] > inventory[most]:
                most = item
            if inventory[item] < inventory[least]:
                least = item
        print(f"Item most abundant: {most} with quantity {inventory[most]}")
        print(f"Item least abundant: {least} with quantity {inventory[least]}")
    else:
        print("No items to analyze")
    inventory.update({"magic_item": 1})
    print(f"Updated inventory: {inventory}")


if __name__ == "__main__":
    main()
