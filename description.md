**Description**

Once again we return to **Ajobshohor**, the capital city and the heart of **Ajobdesh**. **Ajobshohor’s** road system can be represented as a tree. There are **n** tollbooths, connected with **n - 1** roads. Each tollbooth has an **x-factor** associated with it. That is, the government has issued a new regulation, where every person traveling via that tollbooth has to pay an amount which is determined by a formula of  **F(x)**. However, the government can reissue the **x-factor** associated with any tollbooth, and  update it in a single day.

**F (x)  => F (x -1)  *  k + F (x - 3) * k  - 2**

**F (1)  => 1**

**F (2)  => 3**

**F (3)  => 5**

John is a freshly graduate software engineer who is relocating to **Ajobshohor** for his new internship; where he will stay for a duration of **q** days. Since his company has a rather flexible working environment, John can sometimes work remotely from his home; but on regular days he has to travel from point **u** to **v**.
 For each of the **q** days, you have to either find the total amount spent by John commuting via the tollbooths, or update the **x-factor** of the tollbooth due to reissuance of the government.

So the two types of queries are.


* Type 1: 
    * 1 u v, print the total toll paid by John, going from point **u** to **v**.
* Type 2: 
    * 2 u x, update the **x-factor** of tollbooth **u**.

As the sum can be quite big, print the sum modulo **10<sup>9</sup>+7**.

**Input**

The first line contains three integers **n**, **q** and **k** ( **1 ≤ n, q ≤ 10<sup>5</sup>** , and **1 <= k <= 50**). The second line contains **n** integer **x<sub>1</sub>, x<sub>2</sub>, …, x<sub>n</sub>**, where **x<sub>i</sub>** is the initial **x-factor** of the node **i**. Each of the next **n - 1** lines contains two integer **ui**, **vi**, ( **1 <= u<sub>i</sub>, v<sub>i</sub> <= n** ), meaning there is an edge between **u<sub>i</sub>** and **v<sub>i</sub>**. Each of the next **q** lines contains a query as described above.

**Constraints**

**1 ≤ n, q ≤ 10<sup>5</sup>**

**2 <= k <= 50**

**1 <= x<sub>i</sub> <= 10<sup>18</sup>**

**1 ≤ u<sub>i</sub> , v<sub>i</sub> ≤ n**


**Output**
For each query of type **1**. print the **sum** in a new line.

**Notes**