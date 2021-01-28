function tensor
    scores = [
        95 83 76
        99 89 82
    ];
    scores(2, 3, 1, 1, 1, 1)
    mean_by_student = mean(scores, 1)
    ndims(mean_by_student)
    mean_by_test = mean(scores, 2)
    ndims(mean_by_test)
    cell_scores = {
        [95 83]
        [99 89 82]
    }
end
