main <- function() {
    scores <- array(
        data = c(c(95, 99), c(83, 89), c(76, 82)),
        dim = c(2, 3),
        dimnames = list(c("Test 1", "Test 2"), c("Alice", "Bob", "Carrie"))
    )
    print(scores)
    # print(dim(scores))
    # print(length(dim(scores)))
    print(scores[1, c(1, 2)])
    print(scores["Test 1", c("Alice", "Bob")])
    # print(scores[, 1])
    # print(scores[, 1:2])
    # print(scores[, seq(2, 1, by = -1)])
    # # print(scores[,,1])
    print(colMeans(scores))
    print(rowMeans(scores))
}

main()
