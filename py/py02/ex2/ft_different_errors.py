def garden_operations(operation_number: int) -> None:
    match operation_number:
        case 0:
            int("abc")
        case 1:
            10 / 0
        case 2:
            open("/non/existent/file")
        case 3:
            "abc" + 1
        case _:
            return


def test_error_types() -> None:
    print("=== Garden Error Types Demo ===")
    for operation_number in [0, 1, 2, 3, 4]:
        print(f"Testing operation {operation_number}...")
        try:
            garden_operations(operation_number)
            print("Operation completed successfully")
        except ValueError as e:
            print(f"Caught ValueError: {e}")
        except ZeroDivisionError as e:
            print(f"Caught ZeroDivisionError: {e}")
        except FileNotFoundError as e:
            print(f"Caught FileNotFoundError: {e}")
        except TypeError as e:
            print(f"Caught TypeError: {e}")
    print("All error types tested successfully!")


if __name__ == "__main__":
    test_error_types()
