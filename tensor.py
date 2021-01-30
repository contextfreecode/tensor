def main():
    from numpy import array
    scores = array([[95, 83, 76], [99, 89, 82]])
    print(scores)
    print(scores.mean(axis=0))
    print(scores.mean(axis=1))
    print(scores.mean(axis=1, keepdims=True))


if __name__ == "__main__":
    main()
