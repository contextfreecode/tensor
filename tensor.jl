using Statistics

function main()
  array = [1 2 3; 4 5 6]
  say(array)

  println("\nsums")
  say(sum(array, dims=1))
  say(sum(array, dims=2))

  println("\nslices")
  say(array[2, :])
  say(array[:, 2])
  say(array[:, 1:2:end])
  say(array[end:-1:1, :])
end

function say(array)
  display(array)
  println()
end

main()
