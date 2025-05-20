class StackParamRunnable implements Runnable {
    private final int id;

    public StackParamRunnable(int id) {
        this.id = id;
    }

    public void run() {
        System.out.println("Runnable Thread with ID: " + id);
    }

    public static void main(String[] args) {
        Thread t1 = new Thread(new StackParamRunnable(1001));
        Thread t2 = new Thread(new StackParamRunnable(1002));

        t1.start();
        t2.start();
    }
}
