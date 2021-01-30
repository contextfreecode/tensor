scores ← 2 3 ⍴ 95 83 76 99 89 82
⍴⍴ scores
⍴⍴ (95 83 76) (99 89 82)
≡ scores
≡ (95 83 76) (99 89 82)

rowMean ← {+⌿⍵÷≢⍵}
colMean ← {rowMean ⍉⍵}
axisMean ← {+/[⍺]⍵÷⍺⌷⍴⍵}

rowMean scores
colMean scores
1 axisMean scores
2 axisMean scores

⍝ a ← 2 3 4 ⍴ ⍳24
