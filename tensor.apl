scores ← 2 3 ⍴ 95 83 76 99 89 82
⍴⍴ scores
⍴⍴ (95 83 76) (99 89 82)
≡ scores

(+/[1]÷≢) scores
(+/[1]÷≢)(⍉scores)

mean_row ← +/[1]÷≢
mean_col ← mean_row ⍉

(+/[1] ÷ (1⌷⍴)) scores

⍝ mean ← {+/[⍵] ÷ ⍵⌷⍴}
