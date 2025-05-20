class MyRunnable implements Runnable {
    private final String name;

    public MyRunnable(String name) {
        this.name = name;
    }

    public void run() {
        for (int i = 1; i <= 3; i++) {
            System.out.println(name + " - Count: " + i);
            try {
                Thread.sleep(500);
            } catch (InterruptedException e) {
                System.out.println(e);
            }
        }
    }

    public static void main(String[] args) {
        Thread t1 = new Thread(new MyRunnable("Thread A"));
        Thread t2 = new Thread(new MyRunnable("Thread B"));

        t1.start();
        t2.start();

        try {
            t1.join();
            t2.join();
        } catch (InterruptedException e) {
            System.out.println(e);
        }

        System.out.println("Main thread finished.");
    }
}
