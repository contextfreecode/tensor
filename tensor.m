function tensor
    scores = [
        95 83 76
        99 89 82
    ]
    old = scores;
    scores(1, 2) = 85;
    old
    scores
    % mean(scores, 1)
    % mean(scores, 2)
    % flat = scores(:)
    % ndims(scores)
    % ndims(flat)
    % scores(1, 2, 1, 1, 1, 1, 1)
end
