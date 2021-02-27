def main():
    from numpy import array
    from numpy.linalg import matrix_rank

    scores = array([
        [95, 83, 76],
        [99, 89, 82.0],
    ])
    # print(scores.mean(axis=0).ndim)
    # print(scores.mean(axis=1, keepdims=True).ndim)
    # print(scores[0])
    # print(scores[:, ::2])
    # flat = scores.ravel()
    # flat[3] = 97
    # print(flat)
    # print(scores)

    scores[1] = 0.5 * scores[0]
    print(scores)
    print(matrix_rank(scores))


if __name__ == "__main__":
    main()
