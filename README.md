Limit order book and matching engine

Some assumptions and decisions:
- if market order walks the book and is not filled, it will NOT go on the books.
  this is because it would lead to extremely unfavorable fills
