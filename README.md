# 371todo

## Date
dateRegex is updated to accept date arguments such as 2022-1-1. Replace string with comment above to enforce YYYY-MM-DD. Also in str(), uncomment to enforce YYYY-MM-DD output string.

When it comes to the less than operator, uninitialised doesn't matter as they will be set to day, month and year will be set to 0 anyways...

## Task
Not necessary to read. I would use a set to store the tags, but the tests look like it will fail if it's not in order.

## Output
### Save to db
JSON results will be reordered to be in alphabetical order

### Update
If update anywhere fails, no changes get saved.
