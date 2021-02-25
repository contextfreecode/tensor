using Statistics

function main()
  scores = [95 83 76; 99 89 82.0]
  say(scores)
  say(mean(scores, dims=1))
  say(mean(scores, dims=2))
  say(scores[:, 1:2:end])
  say(scores[end:-1:1, :])
end

function say(array)
  display(array)
  println()
end

main()
