import sys


def parse(args: list[str]) -> list[int]:
    """Convert arguments to scores, reporting and skipping invalid ones."""
    scores = []
    for arg in args:
        try:
            scores.append(int(arg))
        except ValueError:
            print(f"Invalid parameter: {arg!r}")
    return scores


def main() -> None:
    """Print score statistics for the command-line arguments."""
    print("=== Player Score Analytics ===")
    scores = parse(sys.argv[1:])
    if not scores:
        print("No scores provided. Usage: python3 ft_score_analytics.py "
              "<score1> <score2> ...")
        return
    print(f"Scores processed: {scores}")
    print(f"Total players: {len(scores)}")
    print(f"Total score: {sum(scores)}")
    print(f"Average score: {sum(scores) / len(scores)}")
    print(f"High score: {max(scores)}")
    print(f"Low score: {min(scores)}")
    print(f"Score range: {max(scores) - min(scores)}")


if __name__ == "__main__":
    main()
