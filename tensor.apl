scores ← 2 3 ⍴ 95 83 76 99 89 82
⍴⍴ scores
⍴⍴ (95 83 76) (99 89 82)
≡ scores
≡ (95 83 76) (99 89 82)

rowMean ← +⌿÷≢
colMean ← rowMean ⍉
axisMean ← {rowMean (⍤((⍴⍴⍵)+1-⍺)) ⍵}

⍝ a ← 2 3 4 ⍴ ⍳24
