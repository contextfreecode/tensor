def main():
    from torch import tensor
    scores = tensor(
        data=[[95, 83, 76], [99, 89, 82.0]],
        names=["test", "student"],
    )
    print(scores)
    print(scores.mean(axis="test"))
    print(scores.mean(axis="student"))


if __name__ == "__main__":
    main()
